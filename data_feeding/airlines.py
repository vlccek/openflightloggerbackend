import requests
import csv
import psycopg2
import io

from dbconfig import DB_CONFIG

# --- Data Source ---
AIRLINES_DATA_URL = "https://raw.githubusercontent.com/jpatokal/openflights/master/data/airlines.dat"


def clean_value(value):
    """Converts the special value '\\N' to None, otherwise returns the value."""
    return None if value == '\\N' else value


def clean_value_country(value):
    """Converts the special value '\\N' to None, otherwise returns the value."""
    return "" if value == '\\N' else value


def import_airlines_data():
    """
    Downloads airline data and imports it into the PostgreSQL database.
    """
    print("Starting airline data import...")

    # 1. Download the data
    try:
        response = requests.get(AIRLINES_DATA_URL)
        response.raise_for_status()  # Raise an exception for bad status codes
        print("Successfully downloaded airline data.")
    except requests.exceptions.RequestException as e:
        print(f"Error: Failed to download data. {e}")
        return

    # Use io.StringIO to treat the downloaded string data as a file
    data_file = io.StringIO(response.text)

    # 2. Parse CSV and prepare data for insertion
    # The columns are: airline_id, name, alias, iata, icao, callsign, country, active
    csv_reader = csv.reader(data_file)

    processed_rows = []
    for row in csv_reader:
        if len(row) != 8:
            print(f"Skipping malformed row: {row}")
            continue

        # Unpack and transform data for each column
        airline_id_str, name, alias, iata, icao, callsign, country, active_str = row

        # Convert 'Y'/'N' to boolean, default to False if invalid
        is_active = (active_str == 'Y')

        # Prepare a tuple with cleaned values. We use the database's default for airline_id.
        processed_rows.append((
            name,
            clean_value(alias),
            clean_value(iata),
            clean_value(icao),
            clean_value(callsign),
            clean_value_country(country),
            is_active
        ))

    print(f"Processed {len(processed_rows)} airlines for import.")

    # 3. Connect to PostgreSQL and insert data
    conn = None
    try:
        conn = psycopg2.connect(**DB_CONFIG)
        cur = conn.cursor()

        # Optional: Clear the table before inserting new data
        print("Clearing existing data from the 'airlines' table...")
        cur.execute("TRUNCATE TABLE airlines RESTART IDENTITY;")

        # Prepare the INSERT statement for bulk insertion
        insert_query = """
                       INSERT INTO airlines (name, alias, iata_code, icao_code, callsign, country, active)
                       VALUES (%s, %s, %s, %s, %s, %s, %s); \
                       """

        # Execute the insert command for all rows at once
        psycopg2.extras.execute_batch(cur, insert_query, processed_rows)

        conn.commit()
        print(f"Successfully inserted {cur.rowcount} records into the 'airlines' table.")

    except psycopg2.Error as e:
        print(f"Database error: {e}")
        if conn:
            conn.rollback()  # Roll back the transaction on error
    finally:
        if conn:
            cur.close()
            conn.close()
            print("Database connection closed.")


if __name__ == "__main__":
    # This allows the script to be run from the command line
    # It also requires psycopg2.extras to be imported, so we do it here.
    try:
        from psycopg2 import extras

        psycopg2.extras = extras
        import_airlines_data()
    except ImportError:
        print("Please install psycopg2-binary: pip install psycopg2-binary")

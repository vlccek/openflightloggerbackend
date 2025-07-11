import requests
import csv
import io
import psycopg2
from psycopg2 import Error
import warnings  # To suppress InsecureRequestWarning if verify=False is used

from dbconfig import DB_CONFIG
CSV_URL = "https://davidmegginson.github.io/ourairports-data/airports.csv"


def load_airports_data_to_db():
    """
    Downloads airport data from a CSV URL and loads it into a PostgreSQL database.
    """
    conn = None
    try:
        print("Connecting to the database...")
        conn = psycopg2.connect(**DB_CONFIG)
        cur = conn.cursor()
        print("Database connection successful.")

        print(f"Downloading CSV from {CSV_URL}...")

        # Suppress the InsecureRequestWarning if verify=False is used
        with warnings.catch_warnings():
            warnings.simplefilter("ignore", requests.packages.urllib3.exceptions.InsecureRequestWarning)
            response = requests.get(CSV_URL, verify=False)  # Keep verify=False for now as it worked previously

        response.raise_for_status()  # Raise an HTTPError for bad responses (4xx or 5xx)
        print("CSV downloaded successfully.")

        # Use io.StringIO to treat the string content as a file
        csv_file_content = io.StringIO(response.text)
        reader = csv.reader(csv_file_content)

        header = next(reader)  # Skip the header row
        print(f"CSV Header: {header}")

        # Define the order of columns as they should appear in the SQL INSERT statement
        # 'id' is now included at the beginning
        db_columns_order = [
            'id', 'ident', 'type', 'name', 'latitude_deg', 'longitude_deg',
            'elevation_ft', 'continent', 'iso_country', 'iso_region',
            'municipality', 'scheduled_service', 'icao_code', 'iata_code',
            'gps_code', 'local_code', 'home_link', 'wikipedia_link', 'keywords'
        ]

        # Create a mapping from CSV header name to its index, for robust parsing
        csv_header_to_index = {col: i for i, col in enumerate(header)}

        # SQL INSERT statement.
        # ON CONFLICT (id) DO NOTHING handles cases where you might run the script
        # multiple times and want to avoid inserting duplicate IDs.
        insert_sql = f"""
        INSERT INTO airports ({', '.join(db_columns_order)})
        VALUES ({', '.join(['%s'] * len(db_columns_order))})
        ON CONFLICT (id) DO NOTHING;
        """

        print("Starting data insertion...")
        row_count = 0
        batch_size = 1000  # Process rows in batches for better performance
        data_batch = []

        for i, row in enumerate(reader):
            # Map CSV data to DB column order and perform necessary type conversions
            processed_row_data = []

            # id (INTEGER) - Get from CSV and convert to int
            try:
                processed_row_data.append(int(row[csv_header_to_index['id']]))
            except ValueError:
                print(f"Skipping row {i+2} due to invalid ID: {row[csv_header_to_index['id']]}")
                continue # Skip this row if ID is not a valid integer

            # ident (VARCHAR)
            processed_row_data.append(row[csv_header_to_index['ident']] if row[csv_header_to_index['ident']] else None)

            # type (airport_type_enum) - Handle 'closed' to 'closed_airport' mapping
            airport_type = row[csv_header_to_index['type']]
            if airport_type == 'closed':
                processed_row_data.append('closed_airport')
            else:
                processed_row_data.append(airport_type if airport_type else None)

            # name (VARCHAR)
            processed_row_data.append(row[csv_header_to_index['name']] if row[csv_header_to_index['name']] else None)

            # latitude_deg (NUMERIC)
            try:
                processed_row_data.append(float(row[csv_header_to_index['latitude_deg']]) if row[
                    csv_header_to_index['latitude_deg']] else None)
            except ValueError:
                processed_row_data.append(None)  # Handle cases where lat/long might not be valid numbers

            # longitude_deg (NUMERIC)
            try:
                processed_row_data.append(float(row[csv_header_to_index['longitude_deg']]) if row[
                    csv_header_to_index['longitude_deg']] else None)
            except ValueError:
                processed_row_data.append(None)

            # elevation_ft (INTEGER)
            try:
                processed_row_data.append(
                    int(row[csv_header_to_index['elevation_ft']]) if row[csv_header_to_index['elevation_ft']] else None)
            except ValueError:
                processed_row_data.append(None)

            # continent (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['continent']] if row[csv_header_to_index['continent']] else None)

            # iso_country (CHAR)
            processed_row_data.append(
                row[csv_header_to_index['iso_country']] if row[csv_header_to_index['iso_country']] else None)

            # iso_region (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['iso_region']] if row[csv_header_to_index['iso_region']] else None)

            # municipality (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['municipality']] if row[csv_header_to_index['municipality']] else None)

            # scheduled_service (BOOLEAN) - 'yes' -> True, 'no' -> False
            scheduled_service_val = row[csv_header_to_index['scheduled_service']].lower()
            processed_row_data.append(True if scheduled_service_val == 'yes' else False)

            # icao_code (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['icao_code']] if row[csv_header_to_index['icao_code']] else None)

            # iata_code (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['iata_code']] if row[csv_header_to_index['iata_code']] else None)

            # gps_code (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['gps_code']] if row[csv_header_to_index['gps_code']] else None)

            # local_code (VARCHAR)
            processed_row_data.append(
                row[csv_header_to_index['local_code']] if row[csv_header_to_index['local_code']] else None)

            # home_link (TEXT)
            processed_row_data.append(
                row[csv_header_to_index['home_link']] if row[csv_header_to_index['home_link']] else None)

            # wikipedia_link (TEXT)
            processed_row_data.append(
                row[csv_header_to_index['wikipedia_link']] if row[csv_header_to_index['wikipedia_link']] else None)

            # keywords (TEXT)
            processed_row_data.append(
                row[csv_header_to_index['keywords']] if row[csv_header_to_index['keywords']] else None)

            data_batch.append(tuple(processed_row_data))

            if len(data_batch) >= batch_size:
                try:
                    cur.executemany(insert_sql, data_batch)
                    conn.commit()
                    row_count += len(data_batch)
                    print(f"Inserted {row_count} rows so far.")
                    data_batch = []
                except Error as e:
                    conn.rollback()
                    print(f"Error during batch insert at CSV row {i + 2} (including header): {e}")
                    raise

        # Insert any remaining rows in the last batch
        if data_batch:
            try:
                cur.executemany(insert_sql, data_batch)
                conn.commit()
                row_count += len(data_batch)
                print(f"Inserted {row_count} final rows.")
            except Error as e:
                conn.rollback()
                print(f"Error during final batch insert: {e}")
                raise

        print(f"Data loading complete. Total {row_count} rows processed.")

    except requests.exceptions.RequestException as e:
        print(f"Error downloading CSV: {e}")
    except Error as e:
        print(f"Database error: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    finally:
        if conn:
            cur.close()
            conn.close()
            print("Database connection closed.")


if __name__ == "__main__":
    load_airports_data_to_db()
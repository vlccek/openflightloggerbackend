-- Create an ENUM type for the 'type' column
CREATE TYPE airport_type_enum AS ENUM (
    'heliport',
    'small_airport',
    'medium_airport',
    'large_airport',
    'seaplane_base',
    'balloonport',
    'closed_airport'
    );

-- Create the 'airports' table
CREATE TABLE airports
(
    id                SERIAL PRIMARY KEY,
    ident             VARCHAR(20) UNIQUE NOT NULL,
    type              airport_type_enum  NOT NULL, -- Using the custom ENUM type
    name              VARCHAR(255)       NOT NULL,
    latitude_deg      NUMERIC(10, 7)     NOT NULL,
    longitude_deg     NUMERIC(10, 7)     NOT NULL,
    elevation_ft      INTEGER,
    continent         VARCHAR(10),
    iso_country       CHAR(2)            NOT NULL,
    iso_region        VARCHAR(10)        NOT NULL,
    municipality      VARCHAR(100),
    scheduled_service BOOLEAN            NOT NULL, -- Storing 'yes'/'no' as true/false
    icao_code         VARCHAR(4),
    iata_code         VARCHAR(3),
    gps_code          VARCHAR(4),
    local_code        VARCHAR(10),
    home_link         TEXT,
    wikipedia_link    TEXT,
    keywords          TEXT
);



CREATE TABLE airlines
(
    airline_id SERIAL PRIMARY KEY,
    name       VARCHAR(255) NOT NULL,
    alias      VARCHAR(255),
    iata_code  CHAR(5),
    icao_code  CHAR(5),
    callsign   VARCHAR(255),
    country    VARCHAR(255) NOT NULL,
    active     BOOLEAN      NOT NULL
);

CREATE TABLE users
(
    id         SERIAL PRIMARY KEY,
    username   VARCHAR(50) UNIQUE  NOT NULL,
    email      VARCHAR(255) UNIQUE NOT NULL,
    password   VARCHAR(255)        NOT NULL,

    created_at TIMESTAMPTZ         NOT NULL DEFAULT NOW()
);


-- Enum for the type of seat
CREATE TYPE seat_type_enum AS ENUM (
    'window',
    'middle',
    'aisle'
    );

-- Enum for the travel class
CREATE TYPE flight_class_enum AS ENUM (
    'Economy',
    'Premium Economy',
    'Business',
    'First'
    );

-- Enum for the reason for the flight
CREATE TYPE flight_reason_enum AS ENUM (
    'Leisure',
    'Business',
    'Crew',
    'Repositioning',
    'Other'
    );

CREATE TABLE flights
(
    id                   SERIAL PRIMARY KEY,

    -- Foreign key to the user who logged the flight
    user_id              INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,

    -- Foreign keys to the airports table (assuming you have one)
    departure_airport_id INTEGER NOT NULL, -- REFERENCES airports(id),
    arrival_airport_id   INTEGER NOT NULL, -- REFERENCES airports(id),

    -- Flight details
    flight_date          TIMESTAMPTZ NOT NULL,
    flight_duration      INTERVAL, -- Best for storing durations (e.g., '3 hours 30 minutes')
    distance             INTEGER,  -- In kilometers or miles, depending on your standard

    -- Using JSONB to store an array of coordinate pairs for the flight path
    -- Example: '[{"lat": 40.7128, "lon": -74.0060}, {"lat": 34.0522, "lon": -118.2437}]'
    route_path           JSONB,

    -- Aircraft and flight identifiers
    flight_number        VARCHAR(20),
    airplane_type        VARCHAR(50),
    airplane_registration VARCHAR(20),

    -- Seat and class information using the ENUMs defined above
    seat                 VARCHAR(4),
    seat_type            seat_type_enum,
    flight_class         flight_class_enum,
    flight_reason        flight_reason_enum,

    -- Timestamps for record management
    created_at           TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    edited_at           TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

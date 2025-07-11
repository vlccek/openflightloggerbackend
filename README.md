# Flight Logger Backend

This project is the backend for a flight logging application, built using the Drogon C++ web framework.

## API Endpoints

This section details the available API endpoints and how to interact with them.

### Airports

#### `GET /airports`

Retrieves a list of airports. This endpoint now supports a single search parameter that queries across multiple fields.

**Query Parameters:**

*   `search`: A single search term that will be used to find matches in the `ident`, `name`, `municipality`, `icao_code`, `iata_code`, `gps_code`, `local_code`, and `keywords` fields. The search is case-insensitive and performs partial matching.

**Note:** This endpoint also implicitly filters out airports of `type` 'heliport'.

**Example Usage:**

*   Get all airports (returns an empty array if no search term is provided):
    ```
    GET /airports
    ```
*   Search for airports containing "London" in any of the searchable fields:
    ```
    GET /airports?search=London
    ```
*   Search for airports with ICAO code "KJFK" or containing "KJFK" in other fields:
    ```
    GET /airports?search=KJFK
    ```

#### `POST /airports`

Creates a new airport entry.

**Request Body:**

```json
{
    "ident": "string",
    "type": "string",
    "name": "string",
    "latitude_deg": "number",
    "longitude_deg": "number",
    "elevation_ft": "integer",
    "continent": "string",
    "iso_country": "string",
    "iso_region": "string",
    "municipality": "string",
    "scheduled_service": "boolean",
    "icao_code": "string",
    "iata_code": "string",
    "gps_code": "string",
    "local_code": "string",
    "home_link": "string",
    "wikipedia_link": "string",
    "keywords": "string"
}
```

#### `GET /airports/{id}`

Retrieves a single airport by its primary key (ID).

**Path Parameters:**

*   `id`: The primary key of the airport.

**Example Usage:**

```
GET /airports/123
```

#### `PUT /airports/{id}`

Updates an existing airport entry identified by its primary key (ID).

**Path Parameters:**

*   `id`: The primary key of the airport to update.

**Request Body:**

(Similar to POST, but only include fields you wish to update. All fields are optional for update.)

```json
{
    "ident": "string",
    "type": "string",
    "name": "string",
    "latitude_deg": "number",
    "longitude_deg": "number",
    "elevation_ft": "integer",
    "continent": "string",
    "iso_country": "string",
    "iso_region": "string",
    "municipality": "string",
    "scheduled_service": "boolean",
    "icao_code": "string",
    "iata_code": "string",
    "gps_code": "string",
    "local_code": "string",
    "home_link": "string",
    "wikipedia_link": "string",
    "keywords": "string"
}
```

#### `DELETE /airports/{id}`

Deletes an airport entry identified by its primary key (ID).

**Path Parameters:**

*   `id`: The primary key of the airport to delete.

**Example Usage:**

```
DELETE /airports/123
```

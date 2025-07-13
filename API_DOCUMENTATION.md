
# API Documentation

This document provides a detailed description of the API endpoints available in the Flight Logger application.

## Authentication

### POST /api/v1/login

Authenticates a user and returns a JWT token.

**Request Body:**

*   `email` (string, required): The user's email address.
*   `password` (string, required): The user's password.
*   `remember` (boolean, optional): If true, the token will have a longer expiration time.

**Response:**

*   `token` (string): The JWT token.
*   `expiresIn` (integer): The number of seconds until the token expires.
*   `expiresAt` (integer): The timestamp when the token expires.
*   `status` (integer): 1 for success, 0 for failure.
*   `error` (string, optional): An error message if authentication fails.

### GET /api/v1/verify

Verifies a JWT token.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Response:**

*   `aud` (string): The audience of the token.
*   `exp` (integer): The expiration time of the token.
*   `iat` (integer): The time the token was issued.
*   `iss` (string): The issuer of the token.
*   `nbf` (integer): The time before which the token is not valid.
*   `email` (string): The email address of the user.
*   `jwt_debugger` (string): A URL to debug the token on jwt.io.
*   `status` (integer): 1 for success.

### POST /api/v1/register

Registers a new user.

**Request Body:**

*   `username` (string, required): The user's username.
*   `email` (string, required): The user's email address.
*   `password` (string, required): The user's password.

**Response:**

*   `status` (integer): 1 for success, 0 for failure.
*   `message` (string, optional): A success message.
*   `error` (string, optional): An error message if registration fails.

## Airports

### GET /api/v1/airports

Retrieves a list of airports.

**Query Parameters:**

*   `search` (string, optional): A search term to filter airports by ident, name, municipality, ICAO code, IATA code, GPS code, local code, or keywords.

**Response:**

An array of airport objects.

### GET /api/v1/airports/{id}

Retrieves a single airport by its ID.

**Response:**

An airport object.

### POST /api/v1/airports

Creates a new airport.

**Request Body:**

An airport object.

**Response:**

The created airport object.

### PUT /api/v1/airports/{id}

Updates an existing airport.

**Request Body:**

An airport object.

**Response:**

*   Status code 202 if successful.

### DELETE /api/v1/airports/{id}

Deletes an airport.

**Response:**

*   Status code 204 if successful.

## Flights

### GET /api/v1/flights

Retrieves a list of flights for the authenticated user.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Response:**

An array of flight objects.

### GET /api/v1/flights/{id}

Retrieves a single flight by its ID.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Response:**

A flight object.

### POST /api/v1/flights

Creates a new flight.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Request Body:**

A flight object.

**Response:**

The created flight object.

### PUT /api/v1/flights/{id}

Updates an existing flight.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Request Body:**

A flight object.

**Response:**

*   Status code 200 if successful.

### DELETE /api/v1/flights/{id}

Deletes a flight.

**Request Headers:**

*   `Authorization` (string, required): The JWT token, prefixed with "Bearer ".

**Response:**

*   Status code 200 if successful.

## Default

### GET /

Lists all available API routes.

**Response:**

*   `available_routes` (array): A list of available routes.
*   `total_routes` (integer): The total number of available routes.

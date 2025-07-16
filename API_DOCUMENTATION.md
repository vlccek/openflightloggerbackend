# Flight Logger API Specification

## Authentication

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/auth/login` | POST | - | `{"email": "", "password": ""}` | - | `{"token": "", "expiresAt": 0, "status": 1, "error": ""}` |
| `/api/v1/auth/refresh` | POST | `Authorization: Bearer {token}` (required) | - | - | `{"aud": "", "exp": 0, "iat": 0, "iss": "", "nbf": 0, "email": "", "jwt_debugger": "", "status": 1}` |
| `/api/v1/auth/register` | POST | - | `{"username": "", "email": "", "password": ""}` | - | `{"status": 1, "message": "", "error": ""}` |

## Airports

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/airports` | GET | - | - | `?search={term}` (optional) | `[{"id": 0, "ident": "", "name": "", "municipality": ""}]` |
| `/api/v1/airports/{id}` | GET | - | - | - | `{"id": 0, "ident": "", "name": "", "municipality": ""}` |
| `/api/v1/airports` | POST | - | `{"ident": "", "name": "", "municipality": ""}` | - | `{"id": 0, "ident": "", "name": "", "municipality": ""}` |
| `/api/v1/airports/{id}` | PUT | - | `{"ident": "", "name": "", "municipality": ""}` | - | `{"status": 202}` |
| `/api/v1/airports/{id}` | DELETE | - | - | - | `{"status": 204}` |

**Note:** The `search` parameter filters airports by ident, name, municipality, ICAO code, IATA code, GPS code, local code, or keywords.

## Flights

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/myflights` | GET | `Authorization: Bearer {token}` (required) | - | `?lastEdited={timestamp}` (optional) | `[{"id": 0, "user_id": 0, "flight_number": "", "flight_reason": "", "edited_at": ""}]` |
| `/api/v1/myflights/{id}` | GET | `Authorization: Bearer {token}` (required) | - | - | `{"id": 0, "user_id": 0, "flight_number": "", "flight_reason": "", "edited_at": ""}` |
| `/api/v1/myflights` | POST | `Authorization: Bearer {token}` (required) | `{"departure_airport_id": 0, "arrival_airport_id": 0, "flight_date": "YYYY-MM-DDTHH:MM:SSZ", "flight_duration": "", "distance": 0, "route_path": [], "flight_number": "", "airplane_type": "", "airplane_registration": "", "seat": "", "seat_type": "", "flight_class": "", "flight_reason": ""}` | - | `{"id": 0, "user_id": 0, "flight_number": "", "flight_reason": "", "edited_at": ""}` |
| `/api/v1/myflights/{id}` | PUT | `Authorization: Bearer {token}` (required) | `{"flight_number": "", "flight_reason": ""}` | - | `{"message": "Updated successfully"}` |
| `/api/v1/myflights/{id}` | DELETE | `Authorization: Bearer {token}` (required) | - | - | `{"message": "Deleted successfully"}` |
| `/api/v1/myflights/latestEditedDate` | GET | `Authorization: Bearer {token}` (required) | - | - | `{"latestEditedDate": "YYYY-MM-DDTHH:MM:SSZ"}` |

## Default

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/` | GET | - | - | - | `{"available_routes": [], "total_routes": 0}` |

## Common Query Parameter Patterns

Based on the API specification, here are the common query parameter patterns:

- **Search functionality**: `?search={term}` - Used for filtering results
- **Path parameters**: `{id}` - Used for resource identification in the URL path
- **Authentication**: Uses Bearer token in Authorization header, not query parameters
- **Filtering by last edited date**: `?lastEdited={timestamp}` - Used for filtering flights edited after a specific timestamp.

## Notes

- All authenticated endpoints require the `Authorization` header with format: `Bearer {your_jwt_token}`
- Path parameters like `{id}` are part of the URL path, not query parameters
- Response status codes vary by endpoint (200, 202, 204 for different operations)
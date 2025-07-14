# Flight Logger API Specification

## Authentication

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/login` | POST | - | `?email={}&password={}` | - | `{"token": "", "expiresAt": 0, "status": 1, "error": ""}` |
| `/api/v1/verify` | GET | `Authorization: Bearer {token}` (required) | - | - | `{"aud": "", "exp": 0, "iat": 0, "iss": "", "nbf": 0, "email": "", "jwt_debugger": "", "status": 1}` |
| `/api/v1/register` | POST | - | `?username={}&email={}&password={}` | - | `{"status": 1, "message": "", "error": ""}` |

## Airports

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/airports` | GET | - | - | `?search={term}` (optional) | `[{"id": 0, "ident": "", "name": "", "municipality": ""}]` |
| `/api/v1/airports/{id}` | GET | - | - | - | `{"id": 0, "ident": "", "name": "", "municipality": ""}` |
| `/api/v1/airports` | POST | - | `?ident={}&name={}&municipality={}` | - | `{"id": 0, "ident": "", "name": "", "municipality": ""}` |
| `/api/v1/airports/{id}` | PUT | - | `?ident={}&name={}&municipality={}` | - | `{"status": 202}` |
| `/api/v1/airports/{id}` | DELETE | - | - | - | `{"status": 204}` |

**Note:** The `search` parameter filters airports by ident, name, municipality, ICAO code, IATA code, GPS code, local code, or keywords.

## Flights

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/api/v1/flights` | GET | `Authorization: Bearer {token}` (required) | - | - | `[{"id": 0, "date": "", "departure": "", "arrival": "", "duration": 0}]` |
| `/api/v1/flights/{id}` | GET | `Authorization: Bearer {token}` (required) | - | - | `{"id": 0, "date": "", "departure": "", "arrival": "", "duration": 0}` |
| `/api/v1/flights` | POST | `Authorization: Bearer {token}` (required) | `?date={}&departure={}&arrival={}&duration={}` | - | `{"id": 0, "date": "", "departure": "", "arrival": "", "duration": 0}` |
| `/api/v1/flights/{id}` | PUT | `Authorization: Bearer {token}` (required) | `?date={}&departure={}&arrival={}&duration={}` | - | `{"status": 200}` |
| `/api/v1/flights/{id}` | DELETE | `Authorization: Bearer {token}` (required) | - | - | `{"status": 200}` |

## Default

| Endpoint | Method | Headers | Request Body | Query Parameters | Response |
|----------|--------|---------|--------------|------------------|----------|
| `/` | GET | - | - | - | `{"available_routes": [], "total_routes": 0}` |

## Common Query Parameter Patterns

Based on the API specification, here are the common query parameter patterns:

- **Search functionality**: `?search={term}` - Used for filtering results
- **Path parameters**: `{id}` - Used for resource identification in the URL path
- **Authentication**: Uses Bearer token in Authorization header, not query parameters

## Notes

- All authenticated endpoints require the `Authorization` header with format: `Bearer {your_jwt_token}`
- Path parameters like `{id}` are part of the URL path, not query parameters
- The only query parameter mentioned in the specification is `search` for the airports endpoint
- Response status codes vary by endpoint (200, 202, 204 for different operations)
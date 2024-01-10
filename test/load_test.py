import requests
import concurrent.futures

# Replace with the URL of your web server
url = "http://localhost:7717"

# Number of concurrent requests to simulate
concurrent_requests = 100

# Function to make a GET request to the web server
def make_request():
    try:
        response = requests.get(url)
        # Print the status code for verification
        print(f"Status Code: {response.status_code}")
    except Exception as e:
        print(f"Error: {e}")

# Create a pool of threads to execute concurrent requests
with concurrent.futures.ThreadPoolExecutor(max_workers=concurrent_requests) as executor:
    # Submit the function for execution multiple times concurrently
    futures = [executor.submit(make_request) for _ in range(concurrent_requests)]

    # Wait for all tasks to complete
    concurrent.futures.wait(futures)

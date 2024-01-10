import requests
import json
import concurrent.futures
import random

# Replace with the URL of your web server
url = "http://localhost:7717/book"

# Number of concurrent requests to simulate
concurrent_requests = 10

# Function to make a POST request to the web server with a random JSON body
def make_post_request():
    try:
        # Generate a random JSON body
        random_data = {
            "id": f"{random.randint(1, 100)}",
            "title": f"Book Title {random.randint(1, 100)}",
            "author": f"Author {random.randint(1, 100)}"
        }

        # Convert the dictionary to a JSON string
        json_data = json.dumps(random_data)

        # Make the POST request
        response = requests.post(url, data=json_data, headers={"Content-Type": "application/json"})

        # Print the status code and response for verification
        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
    except Exception as e:
        print(f"Error: {e}")

# Create a pool of threads to execute concurrent POST requests
with concurrent.futures.ThreadPoolExecutor(max_workers=concurrent_requests) as executor:
    # Submit the function for execution multiple times concurrently
    futures = [executor.submit(make_post_request) for _ in range(concurrent_requests)]

    # Wait for all tasks to complete
    concurrent.futures.wait(futures)

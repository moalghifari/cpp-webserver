import requests
import json
import concurrent.futures
import random

url = "http://localhost:7717/book"

concurrent_requests = 10

def make_post_request():
    try:
        random_data = {
            "id": f"{random.randint(1, 100)}",
            "title": f"Book Title {random.randint(1, 100)}",
            "author": f"Author {random.randint(1, 100)}"
        }

        json_data = json.dumps(random_data)

        response = requests.post(url, data=json_data, headers={"Content-Type": "application/json"})

        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
    except Exception as e:
        print(f"Error: {e}")

with concurrent.futures.ThreadPoolExecutor(max_workers=concurrent_requests) as executor:
    futures = [executor.submit(make_post_request) for _ in range(concurrent_requests)]
    concurrent.futures.wait(futures)

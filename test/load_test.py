import requests
import concurrent.futures

url = "http://localhost:7717"

concurrent_requests = 100

def make_request():
    try:
        response = requests.get(url)
        print(f"Status Code: {response.status_code}")
    except Exception as e:
        print(f"Error: {e}")

with concurrent.futures.ThreadPoolExecutor(max_workers=concurrent_requests) as executor:
    futures = [executor.submit(make_request) for _ in range(concurrent_requests)]
    concurrent.futures.wait(futures)

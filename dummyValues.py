import requests
import random
import time
from dotenv import load_dotenv
import os

load_dotenv() 
api_url = os.getenv('API_URL')

def main():
    while True:
        humidity = random.randint(30, 80)
        data = {
            "sensor_id": 1,
            "humidity": humidity
        }
        response = requests.post(api_url, json=data)
        if response.status_code == 200:
            print(f"Data sent: {data}")
        else:
            print(f"Error sending data: {response.status_code}")
        time.sleep(2)  # every 2 sec send data 


if __name__ == "__main__": 
    try: 
        main()
    except KeyboardInterrupt: 
        pass
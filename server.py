from collections import namedtuple
from dotenv import load_dotenv
from fabric import Connection
from multiprocessing import cpu_count
from statistics import mean
from os import getenv
import requests

load_dotenv()

Host = namedtuple("Stats", ["Server", "Temp"])


def convert_from_kelvin(temp):
    if isinstance(temp, str):
        temp = int(temp)

    return (temp - 271.15) * (9/5) + 32


def read_weather_data(city):
    api_key = "2353371c61fb3b07afd93fa3843e9c71"
    url = "https://api.openweathermap.org/data/2.5/weather"
    r = requests.get(f"{url}?q={city}&APPID={api_key}")
    data = r.json()

    return Host(data["name"], convert_from_kelvin(data["main"]["temp"]))


def average_core_temps(c):
    sensors = c.run("sensors", hide=True).stdout.strip()
    sensors = sensors.split("\n")[3:(cpu_count() // 2) + 3]
    sensors = mean([float(line.split(" ")[9][1:]) for line in sensors])

    return sensors


def read_server_temp():
    host_stats = []
    for i in range(1, 10):
        ip = getenv(f"SERVER_{i}_IP")
        hostname = getenv(f"SERVER_{i}_HOST")
        username = getenv(f"SERVER_{i}_USER")
        password = getenv(f"SERVER_{i}_PW")

        # Dip out if any of these are unset
        if not any([ip, hostname, username, password]):
            break

        host_string = f"{username}@{ip}"
        connect_kwargs = {"password": password}

        c = Connection(host=host_string, connect_kwargs=connect_kwargs)
        average = average_core_temps(c)
        host_stats.append(Host(hostname, average))

    return host_stats

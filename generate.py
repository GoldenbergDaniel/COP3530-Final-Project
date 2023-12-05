from math import radians, sin, cos, sqrt, atan2
import random
import csv

def generate_cities(num_cities) -> dict:
  cities = []
  for i in range(num_cities):
    city = {
      "id": i,
      "latitude": round(random.uniform(-90, 90), 2),
      "longitude": round(random.uniform(-180, 180), 2),
      "area": int(random.uniform(1, 1000)),
      "population": random.randint(1000, 10000000),
    }
    city["density"] = int(city["population"] / city["area"])
    cities.append(city)

  return cities


def save_cities_to_csv(cities, path):
  with open(path, mode="w", newline="") as file:
    field_names = ["id", "latitude", "longitude", "area", "population", "density", "adjacent"]
    writer = csv.DictWriter(file, fieldnames=field_names)
    writer.writeheader()
    for city in cities:
      writer.writerow(city)
  file.close()


def distance(lat1, lon1, lat2, lon2) -> float:
  R = 3959.0  # Radius of Earth in miles
  dlat = radians(lat2 - lat1)
  dlon = radians(lon2 - lon1)
  a = sin(dlat / 2)**2 + cos(radians(lat1)) * cos(radians(lat2)) * sin(dlon / 2)**2
  c = 2 * atan2(sqrt(a), sqrt(1 - a))
  dist = R * c
  
  return dist


def find_nearest_cities(cities):
  for city in cities:
    nearest_count = random.randint(1, 3)
    adjacent = sorted(cities, key=lambda other: distance(
                                                         city["latitude"], 
                                                         city["longitude"], 
                                                         other["latitude"], 
                                                         other["longitude"])
                                                )[1:nearest_count+1]      
    city["adjacent"] = [other["id"] for other in adjacent]


city_count: int = 1000
cities: dict = generate_cities(city_count)
find_nearest_cities(cities)
save_cities_to_csv(cities, "cities.csv")

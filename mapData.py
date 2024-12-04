import requests
import pandas as pd

# Overpass Turbo API URL
overpass_url = "http://overpass-api.de/api/interpreter"

# Overpass query to fetch named places excluding "N/A"
overpass_query = """
[out:json][timeout:900];
(
  node["name"]["name"!="N/A"](18.2915,73.6269,18.7507,74.0668);
  way["name"]["name"!="N/A"](18.2915,73.6269,18.7507,74.0668);
  relation["name"]["name"!="N/A"](18.2915,73.6269,18.7507,74.0668);
);
out body;
>;
out skel qt;
"""

# Fetch data from Overpass Turbo API
response = requests.get(overpass_url, params={'data': overpass_query})

if response.status_code == 200:
    data = response.json()
    
    # Convert to DataFrame for processing
    df = pd.json_normalize(data['elements'])
    
    # Remove rows with any "N/A" value or missing values in any column
    df_cleaned = df.dropna()  # Drop rows with missing values
    df_cleaned = df_cleaned.replace("N/A", pd.NA).dropna()  # Drop rows with "N/A"
    
    # Save the cleaned data
    df_cleaned.to_csv("pune_cleaned_places.csv", index=False)
    print("Cleaned data saved to pune_cleaned_places.csv")
else:
    print("Error fetching data:", response.status_code)


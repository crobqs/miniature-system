from pytube import Playlist
import requests
from bs4 import BeautifulSoup

# Playlist URL
playlist_url = "https://www.youtube.com/playlist?list=PLztBpqftvzxXBhbYxoaZJmnZF6AUQr1mH"

# Create Playlist object
playlist = Playlist(playlist_url)

print(f"Fetching details for playlist: {playlist.title}")

# Function to fetch title using BeautifulSoup
def fetch_title(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, "html.parser")
        # Extract title from the <title> tag
        return soup.title.string.replace(" - YouTube", "").strip()
    except Exception as e:
        return f"Error fetching title: {e}"

# Loop through video URLs
for idx, video_url in enumerate(playlist.video_urls, start=1):
    title = fetch_title(video_url)
    print(f"{idx}. {title}")

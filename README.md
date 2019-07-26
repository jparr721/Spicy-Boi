# Spicy Boi
Monitor all those server temps with this easy device

## What is this?
This uses a 4-bit version of a basic LCD screen to display server temperatures. Using a .env file, you can load up all the credentials to grab temps from the system. You'll need to have `sensors` installed on the host for this to work. It also gets the weather (which, right now, is hard coded).

## API
The LCD api is very straightforward. Simply read the code and you'll see exactly how it works. It just writes to the screen and chooses the line to access.

For the weather and server API, it's also just as easy.

### Supported Versions
- This was coded to support python3.5+ becuase raspberry pi's automatically come with Python3.5 installed. As a result, I wanted to decrease friction as much as possible with getting it running.

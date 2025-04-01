# Import libraries
import dotenv
import os
import asyncio
from pylsl import StreamInfo, StreamOutlet
from idun_guardian_sdk import GuardianClient

# Load environment variables
dotenv.load_dotenv()

# IDUN Settings
IDUN_DEVICE_ID = os.getenv("IDUN_DEVICE_NAME")
API_KEY = os.getenv("IDUN_API_KEY")

# Recording settings
RECORDING_TIMER: int = (60 * 120)  # = 60 seconds * n minutes
SRATE = 250  # Sampling rate [Hz]

# Helper functions
async def stop_task(task):
    task.cancel()
    try:
        await task
    except asyncio.CancelledError:
        pass


async def read_battery_30(client):
    while True:
        battery = await client.check_battery()
        print("Battery Level: %s%%" % battery)
        await asyncio.sleep(30)


def check_stop_signal():
    """Check if the stop signal file exists."""
    return os.path.exists("stop_signal.txt")


async def main():
    client = GuardianClient(api_token=API_KEY, debug=True)
    client.address = await client.search_device()

    info = StreamInfo("IDUN", "EEG", 1, SRATE, "float32", client.address)
    lsl_outlet = StreamOutlet(info, 20, 360)

    def lsl_stream_handler(event):
        message = event.message
        eeg = message["raw_eeg"]
        most_recent_ts = eeg[-1]["timestamp"]
        data = [sample["ch1"] for sample in eeg]
        lsl_outlet.push_chunk(data, most_recent_ts)

    client.subscribe_live_insights(
        raw_eeg=True,
        handler=lsl_stream_handler,
    )

    recording_task = asyncio.create_task(client.start_recording(recording_timer=RECORDING_TIMER))
    battery_task = asyncio.create_task(read_battery_30(client))

    while not check_stop_signal():
        await asyncio.sleep(5)  # Non-blocking check for stop signal

    print("Stop signal received. Stopping tasks...")
    await stop_task(recording_task)
    await stop_task(battery_task)

if os.path.exists("stop_signal.txt"):
    os.remove("stop_signal.txt")


if __name__ == "__main__":
    asyncio.run(main())
import asyncio
from pylsl import StreamInfo, StreamOutlet

from idun_guardian_sdk import GuardianClient

RECORDING_TIMER: int = 60 * 60 * 2  # 2 hours
my_api_key = ""

if __name__ == "__main__":
    client = GuardianClient(api_token=my_api_key)
    client.address = asyncio.run(client.search_device())

    info = StreamInfo("IDUN", "EEG", 1, 250, "float32", client.address)
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

    asyncio.run(client.start_recording(recording_timer=RECORDING_TIMER))
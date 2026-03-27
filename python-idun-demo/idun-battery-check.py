"""
Sample script for using the Guardian Earbud Client

Checking battery level
"""

import asyncio

from idun_guardian_sdk import GuardianClient


if __name__ == "__main__":
    client = GuardianClient()

    battery_level = asyncio.run(client.check_battery())
    print("Battery Level: %s%%" % battery_level)
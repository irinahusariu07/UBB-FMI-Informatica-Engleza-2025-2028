def load_settings(filename = "settings.properties"):
    settings = {}
    try:
        with open(filename, "r") as file:
            for line in file:
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                key, value = line.split("=", 1)
                settings[key.strip()] = value.strip()
    except FileNotFoundError:
        print("settings.properties file not found")
    return settings

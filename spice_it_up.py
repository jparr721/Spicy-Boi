from lcd import LCD
from server import read_weather_data, read_server_temp
from time import sleep


def spice_it_up():
    lcd = LCD()
    lcd.lcd_init()
    try:
        while True:
            weather_stats = read_weather_data("Denver")
            server_stats = read_server_temp()

            # Load weather first
            lcd.lcd_byte(lcd.LCD_LINE_1, lcd.LCD_CMD)
            lcd.lcd_string(weather_stats.Server, 1)
            lcd.lcd_byte(lcd.LCD_LINE_2, lcd.LCD_CMD)
            lcd.lcd_string(weather_stats.Temp, 1)

            # Let it hang
            sleep(5)

            # Load servers
            for server in server_stats:
                lcd.lcd_byte(lcd.LCD_LINE_1, lcd.LCD_CMD)
                lcd.lcd_string(server.Server, 1)
                lcd.lcd_byte(lcd.LCD_LINE_2, lcd.LCD_CMD)
                lcd.lcd_String(server.Temp, 1)
                sleep(5)

    except KeyboardInterrupt:
        print("^C -- Exiting...")

    finally:
        lcd.lcd_cleanup()


if __name__ == "__main__":
    spice_it_up()

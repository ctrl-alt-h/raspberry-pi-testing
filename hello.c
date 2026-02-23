#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define VOLTAGE_LOW 0
#define VOLTAGE_HIGH 1

int main(int argc, char **argv) {
	const char *chipname = "gpiochip0";
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int ret;

	chip = gpiod_chip_open_lookup(chipname);
	if (!chip) {
		fprintf(stderr, "Open chip failed\n");
		return 1;
	}

	line = gpiod_chip_get_line(chip, 11);
	if (!line) {
		fprintf(stderr, "Get line failed\n");
		gpiod_chip_close(chip);
		return 1;
	}

	ret = gpiod_line_request_output(line, "blink", VOLTAGE_LOW);
	if (ret < 0) {
		fprintf(stderr, "Request output failed\n");
		gpiod_chip_close(chip);
		return 1;
	}

	printf("Blinking LED on GPIO 11... Press Ctrl+C to stop.\n");
	while (1) {
		gpiod_line_set_value(line, VOLTAGE_HIGH);
		usleep(500000);
		gpiod_line_set_value(line, VOLTAGE_LOW);
		usleep(500000);
	}

	gpiod_line_release(line);
	gpiod_chip_close(chip);
	return 0;
}

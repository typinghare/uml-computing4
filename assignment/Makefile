ZIP_FILENAME = JamesChen.zip

clean:
	rm -f $(ZIP_FILENAME)

ps3b: clean
	zip -ur $(ZIP_FILENAME) ps3b

ps4a: clean
	zip -ur $(ZIP_FILENAME) ps4a

ps4b: clean
	zip -ur $(ZIP_FILENAME) ps4b

ps5: clean
	zip -ur $(ZIP_FILENAME) ps5

ps6: clean
	find $@ -type f ! -name "*.txt" | zip -ur $(ZIP_FILENAME) $@

ps7: clean
	find $@ -type f ! -name "*.txt" | zip -ur $(ZIP_FILENAME) $@
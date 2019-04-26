scripts: $(ANDROID_OUT_DIR)/setup.sh

$(ANDROID_OUT_DIR)/setup.sh: scripts/setup.sh | $(ANDROID_OUT_DIR)
	cp $< $@
	chmod +x $@

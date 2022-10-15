.PHONY: clean All

All:
	@echo "----------Building project:[ SDT - Debug ]----------"
	@"$(MAKE)" -f  "SDT.mk" && "$(MAKE)" -f  "SDT.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ SDT - Debug ]----------"
	@"$(MAKE)" -f  "SDT.mk" clean

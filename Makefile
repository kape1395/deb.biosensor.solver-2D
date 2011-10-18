
build:
	@./build.sh
	@echo "#"
	@echo "# Done. You can upload source DEB to the Ubuntu PPA using the command:"
	@echo "#    $$ dput ppa:kape1395/bio biosensor_*_source.changes"
	@echo "#"

clean:
	rm -rf build

.PHONY: build clean


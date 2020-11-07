#!/usr/bin/make -f
.PHONY: all, build

export GPG_TTY := tty # GPG fix on Macos
export SHELL := /bin/bash
MAKEFLAGS += --no-print-directory

# HELP
# thanks to https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
# And: https://gist.github.com/jed-frey/fcfb3adbf2e5ff70eae44b04d30640ad
help: ## 💡This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

init: ## 📦 Download submodules
	@echo "+ $@"
	@git submodule update --init --recursive

lint: ## 🐳 Lint Dockerfile
	@echo "+ $@"
	@echo todo

build-docker: ##🐳 Build container
	@echo "+ $@"
	@docker build . -t raisin:0.1

build: ##♻️ Build code
	@echo "+ $@"
	@docker run -v $(PWD):/disks/ramfs -it raisin:0.1

exec: ## 🚀 Join container
	@echo "+ $@"
	@docker run -v $(PWD):/disks/ramfs -it raisin:0.1 bash


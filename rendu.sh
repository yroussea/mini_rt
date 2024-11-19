#!/usr/bin/env bash

rm -rf .direnv .envrc en.subject.pdf flake.lock flake.nix

(sleep 1; rm -rf rendu.sh) &

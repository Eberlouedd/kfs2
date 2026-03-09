#!/bin/bash
docker build -t kfs .
docker run --rm -v "$PWD:/kfs" kfs
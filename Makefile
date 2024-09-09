# SPDX-License-Identifier: Apache-2.0

memtrace.so:
	cc -shared -fPIC -o memtrace.so memtrace.c -ldl -pthread

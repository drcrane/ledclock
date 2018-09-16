# Create some Timezone Data for the LED Clock

This is a simple program that creates two numbers per year
the two numbers indicate the start and end of a daylight
saving time in Unix epoch time.

The database is available from:

    https://www.iana.org/time-zones

The one I used is:

    https://data.iana.org/time-zones/releases/tzdb-2018e.tar.lz

## `build.sh`

Running `build.sh` should give this output:

    1711846900 Add an hour? Yes
    2045696401 Add an hour? No
    1887843601 Add an hour? No


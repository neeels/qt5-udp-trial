#!/usr/bin/env bash
# Log bounce_udp output while sending datagrams.

bounce_log="$(tempfile)"
recv1338="$(tempfile)"
recv1339="$(tempfile)"
recv1340="$(tempfile)"

# start UDP bouncer as well as three netcat listeners for the bounced
# datagrams.
./bounce_udp >"$bounce_log" 2>&1 &


nc -4 --recv-only -u -l -p 1338 > "$recv1338" &
nc -4 --recv-only -u -l -p 1339 > "$recv1339" &
nc -6 --recv-only -u -l -p 1340 > "$recv1340" &

sleep .5

# send datagrams to the bouncer. sleep so they are guaranteed to arrive in the
# expected order for below test output verification.

# send using IPv4
echo "Hello UDP v4" | nc -4 --send-only -u 127.0.0.1 1337
sleep .1
echo "FOO,1,2,3,v4" | nc -4 --send-only -u 127.0.0.1 1337
sleep .1
echo "BAR,4,5,6,v4" | nc -4 --send-only -u 127.0.0.1 1337
sleep .1
echo "BAZ,7,8,9,v4" | nc -4 --send-only -u 127.0.0.1 1337
sleep .1

# kill the three receiving netcats
kill %2 %3 %4

# reopen receiving netcats for IPv6 test.
# (This is necessary to make sure netcat is still receiving.)
nc -4 --recv-only -u -l -p 1338 >> "$recv1338" &
nc -4 --recv-only -u -l -p 1339 >> "$recv1339" &
nc -6 --recv-only -u -l -p 1340 >> "$recv1340" &

sleep .5

# send using IPv6
echo "Hello UDP v6" | nc -6 --send-only -u ::1 1337
sleep .1
echo "FOO,1,2,3,v6" | nc -6 --send-only -u ::1 1337
sleep .1
echo "BAR,4,5,6,v6" | nc -6 --send-only -u ::1 1337
sleep .1
echo "BAZ,7,8,9,v6" | nc -6 --send-only -u ::1 1337

sleep .5

# kill bounce_udp and the three receiving netcats
kill %1 %2 %3 %4

results="$(tempfile)"
echo "results file: $results"

for f in "$bounce_log" "$recv1338" "$recv1339" "$recv1340"; do
  cat "$f" >> "$results"
  echo "-----eof-----" >> "$results"
  rm "$f" # remove temp files
done

echo
echo "Results:"
cat "$results"

echo

diff="$(diff -u expected_test_results.txt "$results")"
echo "$diff"
if [ -z "$diff" ]; then
  echo "Test successful."
else
  echo "*** TEST FAILED."
  exit 1
fi

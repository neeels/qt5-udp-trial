#!/usr/bin/env bash
# Log bounce_udp output while sending datagrams.

bounce_log="$(tempfile)"
recv1338="$(tempfile)"
recv1339="$(tempfile)"
recv1340="$(tempfile)"

./bounce_udp >"$bounce_log" 2>&1 &
nc -4 -u -l -p 1338 > "$recv1338" &
nc -4 -u -l -p 1339 > "$recv1339" &
nc -6 -u -l -p 1340 > "$recv1340" &

sleep 1

# netcat refuses to exit by itself, so I background it and kill later.
echo "Hello UDP" | nc -4 -u localhost 1337 &
sleep .5
echo "FOO,1,2,3" | nc -4 -u localhost 1337 &
sleep .5
echo "BAR,4,5,6" | nc -4 -u localhost 1337 &
sleep .5
echo "BAZ,7,8,9" | nc -4 -u localhost 1337 &

sleep 1

kill %1 %2 %3 %4 %5 %6 %7 %8

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

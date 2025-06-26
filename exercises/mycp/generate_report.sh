#!/bin/sh

LOG=test_results.log
OUT=test_report.html

echo "[INFO] Generating HTML report..."

cat <<EOF > "$OUT"
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>mycp Test Report</title>
<style>
body { font-family: monospace; background: #111; color: #eee; padding: 20px; }
.pass { color: #8f8; }
.fail { color: #f88; }
h1 { color: #0af; }
</style>
</head>
<body>
<h1>mycp Test Report</h1>
<pre>
EOF

sed \
  -e 's/✔/<span class="pass">✔<\/span>/g' \
  -e 's/✘/<span class="fail">✘<\/span>/g' \
  -e 's/✅/<span class="pass">✅<\/span>/g' \
  -e 's/❌/<span class="fail">❌<\/span>/g' \
  "$LOG" >> "$OUT"

cat <<EOF >> "$OUT"
</pre>
</body>
</html>
EOF

echo "✅ HTML report saved to $OUT"


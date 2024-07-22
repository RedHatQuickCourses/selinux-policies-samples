<html>
<body>
<h1>
<?php
    $username = "quotesapp";
    $password = "app-password";
    $database = "quotesdb";
    $server = "127.0.0.1";

    $mysqli = new mysqli($server, $username, $password, $database);

    $result = $mysqli->query("SELECT count(quote) FROM famousquotes");
    if ($result) {
        if ($row = $result->fetch_array()) {
            $count = $row[0];
        }
	else {
	    echo "No quotes found.", "\n";
            exit;
	}
        $result->free();
    }

    $id = rand(1, $count);

    $result = $mysqli->query("SELECT quote FROM famousquotes WHERE id = " . strval($id));
    if ($result) {
        if ($row = $result->fetch_array()) {
            $quote = $row[0];
	    echo $quote, "\n";
        }
        else {
	    echo "Internal error", "\n";
	    exit;
	}
        $result->free();
    }

    $mysqli->close();
?>
</h1>
<p>
<a hef="/quotes.php">Another quote</a>
</body>
</html>

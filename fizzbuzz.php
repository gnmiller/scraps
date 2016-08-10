<?php
/**
 * Implementation of fizzbuzz in PHP with some flexibility to brush up
 */
function modulo( $in, $mod )
{
        if( "$in" % "$mod" == 0 ) return true;
        else return false;
}

$test = array( 3, 5 );
$prnt = array( "fizz", "buzz" );
for( $i = 0; $i < count( $test ); $i++ ) {
        if( modulo( "$argv[1]", "$test[$i]" ) ) {
                echo "$prnt[$i]";
        }
}

exit(0);
?>

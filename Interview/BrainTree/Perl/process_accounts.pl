#!/usr/bin/perl

use warnings; 
use strict;
use DBI;

if (($#ARGV ne 3) or ($#ARGV ne 2)) {
    print "USEAGE: \n";
    exit(1);
}


my $driver   = "SQLite";
my $database = 
my $dsn      = "DBI:$driver:dbname=$table";
my $usr      = "";          # User name to accounts db
my $pwd      = "";          # Password to accounts db

    
sub init_logging {
    my $dbh = DBI -> connect( $dsn, $usr, $pwd, { RaiseError => 1 } ) or
                         die( $DBI::errstr );     
    my $stmt = qq(CREATE TABLE IF NOT EXISTS CC_Accounts 
                 ( CC        INT   PRIMARY KEY NOT NULL, 
                   Name      TEXT              NOT NULL,
                   Balance   INT                       ,
                   Allowance INT ););
    $dbh->do($stmt);
    $dbh->disconnect();
}


## CC Checksum
## TODO Add checks for $number -what if its not string of numbers
sub luhn10_check {
    my $number = shift @_;
    my $sum    = 0;
    
    for my $i ( 1 .. length $number ) {
        # If on an odd indexed digit, add to sum; otherwise double the digit
        # If the doubled digit > 9, split the digit and add up its components
        # then add to sum
        if ( $i % 2 eq 1 ) {
            $sum += chop $number;
        } else {
            my $digit = 2 * ( chop $number );
            if ( $digit > 9 ) {
                my $digit2 = chop $digit;
                $sum += ( $digit + $digit2 );
            } else {
                $sum += $digit;
            }
        }
    }
    
    return ( $sum % 10 eq 0  ? 1 : 0 );
}
    
# ADD will create a new credit card for a given name, card number, and limit
# Card numbers should be validated using Luhn 10. New cards start with a $0 
# balance
# Add Lisa 5454545454545454 $3000
sub process_add {
    my $name  = shift @ARGV;
    my $cc    = shift @ARGV;
    my $limit = shift @ARGV;

    # Check that the credit card number qualifies
    if (!luhn10_check($cc)) { 
        print "Error: Credit Card Number Invalid\n"; 
        return $EXIT_ERR;
    }
    
    # Check that limit is a valid value
    ($limit_) = $limit_ =~ /(\d+)/;
    if ($limit_ < 0) {
        print "Error: Limit Invalid\n";
        return $EXIT_ERR;
    }

    my $dbh = DBI->connect( $dsn, $usr, $pwd, { RaiseError => 1 } ) or
                       die( $DBI::errstr );    
    
    my $stmt = qq(INSERT OR IGNORE INTO CC_Accounts 
                 (CC, Name, Balance, Allowance) VALUES (?,?,?,?););
                 
    my $sth  = $dbh->prepare($stmt) or die("DBI Error: Cannot Prepare Stmt\n");
    $sth->execute($cc, $name, 0, $limit_);

    $sth->finish();
    $dbh->disconnect();
}

=pod
- "Charge" will increase the balance of the card associated with the provided 
name by the amount specified
   - Charges that would raise the balance over the limit are ignored as if they 
   were declined
   - Charges against Luhn 10 invalid cards are ignored
   Charge Tom $500
=cut
sub process_charge {
    my $name   = shift @ARGV;
    my $amount = shift @ARGV;
    
    my $dbh = DBI->connect( $dsn, $usr, $pwd, { RaiseError => 1 } ) or
                       die( $DBI::errstr );    
    
    my $stmt = qq(SELECT Balance, Limit FROM CC_Accounts WHERE Name = ?;));
    my $sth  = $dbh->prepare($stmt) or die("DBI Error: Cannot Prepare Stmt\n");
    $sth->execute($name);

    $sth->finish();
    $dbh->disconnect();
    
    

}


sub process_credit {

}


sub process_action {
    my $action = shift @ARGV;
    chomp($action);
    
    if (!($action =~ /^ADD|CHARGE|CREDIT/i)) {
        print "Error: Invalid Command. No action taken\n";
        exit(1);
    }
    
    ## Determine what actions to take
    if    ($action =~ /ADD/i)    { process_add();    }
    elsif ($action =~ /CHARGE/i) { process_charge(); }
    else  ($action =~ /CREDIT/i) { process_credit(); }    
    
}




process_add

feeds-csv-splitter
==================

A simple drush command that splits a CSV file to be imported via Feeds in to several files to be batched

How to use
==========

drush feed-cvs-splitter <original CSV file> --lines-per-file=<Number of line> --data-directory=<Where the source and shell script are>

Exemple: 
--------
drush feed-cvs-splitter country_id.csv --lines-per-file=50 --data-directory=/projects/drupal/country_list/

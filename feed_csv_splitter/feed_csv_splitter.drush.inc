<?php

/**
 * @file
 * Drush integration for feed csv splitter.
 */

/**
 * Implements hook_drush_command().
 */
function feed_csv_splitter_drush_command() {
  $items['feed-cvs-splitter'] = array(
    'callback' => 'feed_csv_splitter_split',
    'description' => dt('Splits a CSV file to be imported via Feeds in to several files to be batched.'),
    'aliases' => array('fcs'),
    'arguments'   => array(
      'source-file' => dt('Source file, to be splitted. Must include the full path.
      Example: "--path-script=/foo/bar/file.csv'),

    ),
    'options' => array(
      'lines-per-file'    => dt('Number of lines per file. Default: 50'),
      'data-directory' => dt('The full system path to the script and data.
         Example: "--path-script=/foo/bar/'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_NONE,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function feed_csv_splitter_drush_help($section) {
  switch ($section) {
    case 'drush:feed-csv-splitter':
      return dt('Lists registered library information.');
  }
}

/**
 * Drush_command callback.
 *
 * @param null $source_file
 * @return mixed
 */
function feed_csv_splitter_split($source_file = NULL) {
  // Check if the argument was passed in.
  if (!isset($source_file)) {
    return drush_set_error('DEVEL_GENERATE_INVALID_INPUT', t('Argument "--source-file" is missing.'));
  }
  $line_per_file = drush_get_option('lines-per-file') ? drush_get_option('lines-per-file') : 50;
  $data_path = drush_get_option('data-directory') ? drush_get_option('data-directory') : NULL;

  if (!isset($data_path)) {
    return drush_set_error('DEVEL_GENERATE_INVALID_INPUT', t('You need to pass the full path to the shell script
     Example: "--path-script=/foo/bar/".'));
  }
  feed_csv_splitter_exec($source_file, $line_per_file, $data_path);
}

/**
 * Execute the shell script that splits the CSV file.
 *
 * @param $source_file
 * @param $line_per_file
 * @param $data_path
 * @return mixed
 */
function feed_csv_splitter_exec($source_file, $line_per_file, $data_path) {
  $result = drush_shell_exec('%s/split-csv.sh %s %s %s', $data_path, $source_file, $line_per_file, $data_path);
  if (!$result) {
    drush_set_error('Oops, there was an error during the split.');
  }

  return $result;
}

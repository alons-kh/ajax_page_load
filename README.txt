AJAX PAGE LOAD WITH PROGRESS BAR
--------------------------------

CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Features
 * Installation
 * Configuration


INTRODUCTION
------------
Module allows load page content without reloading the page with progress bar,
work for HTML5 now.


FEATURES
--------
 * Load content without reloading the page using ajax
   - replace content;
   - replace title;
   - attach js events to replacing content
 * Show progressbar on top of the page and change opacity of content
   while page loading
 * Drush command to download and install the NProgress plugin in
   sites/all/libraries

INSTALLATION
------------------------------
 * Download and install the module as usual.
 * Download the jQuery NProgress plugin (http://ricostacruz.com/nprogress/)
   and install at library folder (sites/all/libraries).
   Drush users can use the command "drush nprogress-plugin".

DRUSH
------
A Drush command is provides for easy installation of the NProgress
plugin itself.

% drush nprogress-plugin

The command will download the plugin and unpack it in "sites/all/libraries".

CONFIGURATION
-------------
Settings module here admin/config/user-interface/ajax-page-load.


REQUIREMENTS
------------
This module requires the following modules:

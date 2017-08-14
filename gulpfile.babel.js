'use strict';

import plugins       from 'gulp-load-plugins';
import yargs         from 'yargs';
import gulp          from 'gulp';
import rimraf        from 'rimraf';
import yaml          from 'js-yaml';
import fs            from 'fs';

// Load all Gulp plugins into one variable
const $ = plugins();

// Load settings from settings.yml
const { COMPATIBILITY, PATHS } = loadConfig();

function loadConfig() {
  let ymlFile = fs.readFileSync('config.yml', 'utf8');
  return yaml.load(ymlFile);
}

// Build the "dist" folder by running all of the below tasks
gulp.task('default',
    gulp.series(clean, gulp.parallel(css, js)));

// Delete the "dist" folder
function clean(done) {
  rimraf(PATHS.dist, done);
}

// Copy css files out of the path folders
function css() {
  return gulp.src(PATHS.css)
    .pipe(gulp.dest(PATHS.dist + '/assets/css'));
}

// Copy js files out of the path folders
function js() {
  return gulp.src(PATHS.js)
    .pipe(gulp.dest(PATHS.dist + '/assets/js'));
}

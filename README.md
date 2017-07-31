# How to create a ZURB Template Sub-Theme
Instead of overriding ZURB Template create a sub-theme via drush.  Once created review your new theme's readme file for more information.

## Create a sub-theme with the default options
```bash
drush zurb "custom theme name"
```

## Create a sub-theme with additional options
```bash
drush zurb "foo bar" "foo_bar"  --description="My supersweet awesome theme"
```
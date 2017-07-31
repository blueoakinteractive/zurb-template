<?php

use Drupal\Core\Link;

/**
 * Implements theme_menu_local_tasks().
 */
function zurb_template_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="visually-hidden">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<div class="button-group">';
    $variables['primary']['#suffix'] = '</div>';
    $output .= \Drupal::service('renderer')->render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="visually-hidden">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<div class="button-group">';
    $variables['secondary']['#suffix'] = '</div>';
    $output .= \Drupal::service('renderer')->render($variables['secondary']);
  }

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function zurb_template_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = array(
    '#markup' => $link['title'],
  );

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $link_text['#suffix'] = '<span class="visually-hidden">' . t('(active tab)') . '</span>';
  }

  $state = !empty($variables['element']['#active']) ? 'active' : 'secondary';
  $link['url']->setOption('attributes', array('class' => array('button', $state)));

  $a_tag = Link::fromTextAndUrl($link_text, $link['url'])->toString();

  return $a_tag;
}

/**
 * Implements theme_preprocess_menu().
 */
function zurb_template_preprocess_menu(&$variables) {
  $variables['attributes']['class'][] = 'menu';
}

/**
 * Implements theme_preprocess_menu__MENU_NAME().
 */
function zurb_template_preprocess_menu__main(&$variables) {
  // TODO: add top bar logic here
}

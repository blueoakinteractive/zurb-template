<?php

use Drupal\Core\Link;

/**
 * Implements theme_menu_local_tasks().
 */
function zurb_template_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="visually-hidden">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<div class="button-group small stacked-for-small">';
    $variables['primary']['#suffix'] = '</div>';
    $output .= \Drupal::service('renderer')->render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="visually-hidden">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<div class="button-group tiny stacked-for-small">';
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
 * Implements hook_preprocess_menu_local_task().
 */
function zurb_template_preprocess_menu_local_task(array &$variables) {
  //$variables['element']['#link']['url']->setOption('attributes', ['class'=>'rounded']);
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
  if ($variables['top_bar'] = theme_get_setting('zurb_template_top_bar_enable')) {
    $top_bar_attributes = new \Drupal\Core\Template\Attribute();

    if (theme_get_setting('zurb_template_top_bar_sticky')) {
      $top_bar_attributes->addClass('sticky', 'large-12');
      $top_bar_attributes->setAttribute('data-sticky', TRUE);
      $top_bar_attributes->setAttribute('data-top-anchor', 'top-bar-sticky-container');
      // 9999999(px) is used as no other bottom anchor stopped the top-bar from
      // jumping back to the top of the screen after scrolling past 50% of the
      // screen. Super silly, but hours of work led to this.
      $top_bar_attributes->setAttribute('data-btm-anchor', 9999999);
      $top_bar_attributes->setAttribute('data-margin-top', 0);
      $top_bar_attributes->setAttribute('data-margin-bottom', 0);
      $top_bar_attributes->setAttribute('data-options', 'stickyOn:small');
      $variables['top_bar_sticky'] = TRUE;
    }

    if ($variables['top_bar'] == 2) {
      $top_bar_attributes->addClass('hide-for-medium');
    }

    if (!empty(theme_get_setting('zurb_template_top_bar_grid'))) {
      $top_bar_attributes->addClass('grid-container');
    }

    $variables['top_bar_attributes'] = $top_bar_attributes;
    $variables['top_bar_menu_text'] = theme_get_setting('zurb_template_top_bar_menu_text');

    if ($back_text = theme_get_setting('zurb_template_top_bar_back_text')) {
      $variables['attributes']['data-back-button'] = "<li class=\"js-drilldown-back\"><a>{$back_text}</a></li>";
    }

    if (!theme_get_setting('zurb_template_top_bar_is_hover')) {
      $variables['attributes']['data-disable-hover'] = 'true';
    }

    // Format the linked site name.
    $site_name = \Drupal::config('system.site')->get('name');
    $title = strip_tags($site_name) . ' ' . t('Home');
    $url = \Drupal\Core\Url::fromRoute('<front>');
    $url->setOption('attributes', array('title' => $title));

    $variables['linked_site_name'] = '';
    if (!empty($variables['site_name'])) {
      $variables['linked_site_name'] = Link::fromTextAndUrl($variables['site_name'], $url)->toString();
    }

    $variables['site_name'] = Link::fromTextAndUrl($site_name, $url)->toString();

    // Embed the search form inside the Top Bar.
    if (theme_get_setting('zurb_template_top_bar_search')) {
      if (\Drupal::moduleHandler()->moduleExists('search')) {
        $search_form = \Drupal::formBuilder()
          ->getForm('Drupal\search\Form\SearchBlockForm');

        // Wrap the search form in proper Top Bar classes.
        $search_form['#prefix'] = '<li>';
        $search_form['#suffix'] = '</li>';

        $variables['top_bar_search'] = $search_form;
      }
    }

  }
}

/**
 * Implements hook_preprocess_links().
 */
function zurb_template_preprocess_links(&$variables) {
  // Add button class to link items.
  if (!empty($variables['links'])) {
    foreach ($variables['links'] as $link_key => $link) {
      $link['link']['#options']['attributes']['class'][] = 'button';
      $variables['links'][$link_key] = $link;
    }
  }
}

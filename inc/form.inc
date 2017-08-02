<?php

use \Drupal\Core\Render\Element;

/**
 * Implements hook_form_alter().
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function zurb_template_form_alter(&$form, &$form_state, $form_id) {
  // Sexy submit buttons
  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
    $form['actions']['submit']['#attributes']['class'][] = 'button';
    $form['actions']['submit']['#attributes']['class'][] = 'primary';
  }

  // Pass form_id to children and grand children for creating theme suggestions later.
  $children = Element::children($form);
  foreach ($children as $child) {
    $form[$child]['#parent_form_id'] = $form_id;
    $grand_children = Element::children($form[$child]);
    foreach ($grand_children as $grand_child) {
      $form[$child][$grand_child]['#parent_form_id'] = $form_id;
    }
  };
}

/**
 * Implements hook_theme_suggestions_HOOK().
 * @param array $suggestions
 * @param array $variables
 */
function zurb_template_theme_suggestions_form_alter(array &$suggestions, array $variables) {
  // Create suggestions based on form id.
  $suggestions[] = 'form__' . $variables['element']['#form_id'];
}

/**
 * Implements hook_theme_suggestions_HOOK().
 * @param array $suggestions
 * @param array $variables
 */
function zurb_template_theme_suggestions_input_alter(array &$suggestions, array $variables) {
  // Create suggestions based on form element type and form id.
  if (!empty($variables['element']['#parent_form_id'])) {
    $suggestions[] = 'input__' . $variables['element']['#parent_form_id'];
    $suggestions[] = 'input__' . $variables['element']['#parent_form_id'] . '__' . $variables['element']['#type'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK().
 * @param array $suggestions
 * @param array $variables
 */
function zurb_template_theme_suggestions_form_element_alter(array &$suggestions, array $variables) {
  // Create suggestions based on form element type and form id.
  if (!empty($variables['element']['#parent_form_id'])) {
    $suggestions[] = 'form_element__' . $variables['element']['#parent_form_id'];
    $suggestions[] = 'form_element__' . $variables['element']['#parent_form_id'] . '__' . $variables['element']['#type'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK().
 * @param array $suggestions
 * @param array $variables
 */
function zurb_template_theme_suggestions_container_alter(array &$suggestions, array $variables) {
  // Create suggestions based on form element type and form id.
  if (!empty($variables['element']['#parent_form_id'])) {
    $suggestions[] = 'container__' . $variables['element']['#parent_form_id'];
    $suggestions[] = 'container__' . $variables['element']['#parent_form_id'] . '__' . $variables['element']['#type'];
  }
}

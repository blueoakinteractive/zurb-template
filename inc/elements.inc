<?php
/**
 * @file
 * Override drupal core message styles.
 */
function zurb_template_status_messages($variables) {
  $display = $variables['message_list'];
  $output = '';

  $status_heading = array(
    'error' => t('Error message'),
    'status' => t('Status message'),
    'warning' => t('Warning message'),
  );

  $status_mapping = array(
    'error' => 'alert',
    'status' => 'success',
    'warning' => 'secondary'
  );

  foreach ($display as $type => $messages) {
    if (isset($status_mapping[$type])) {
      $output .= "<div class=\"callout $status_mapping[$type]\"  data-closable>\n";
    }
    else {
      $output .= "<div class=\"callout\" data-closable>\n";
    }

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="visually-hidden">' . $status_heading[$type] . "</h2>\n";
    }

    if (count($messages) > 1) {
      $output .= '<ul>';
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . '</li>';
      }
      $output .= '</ul>';
    }
    else {
      $output .= $messages[0];
    }

    // Add close button to messages
    $output .= '<button class="close-button" aria-label="Dismiss alert" type="button" data-close><span aria-hidden="true">&times;</span></button>';

    $output .= "</div>\n";
  }

  $output = array(
    '#markup' => $output,
    '#allowed_tags' => ['div', 'button', 'a', 'span', 'h2', 'p', 'ul', 'li'],
  );
  $output = render($output);

  return $output;
}

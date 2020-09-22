<?php

/**
 * @file
 * Functions to support theming content.
 */

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function asebac_theme_suggestions_container_alter(array &$suggestions, array $variables) {
  $element = $variables['element'];
  if (isset($element['#type']) && $element['#type'] == 'view') {
    $suggestions[] = 'container__view__' . $element['#name'];
    $suggestions[] = 'container__view__' . $element['#name'] . '__' . $element['#display_id'];
  }
}

/**
 * Implements hook_preprocess_node().
 */
function asebac_preprocess_node(&$variables) {
  $node = $variables['node'];
  if ($node->bundle() === 'agreement' && $variables['view_mode'] === 'full') {
    $categories = [];
    foreach ($node->field_agreement_category_unlimit as $item) {
      $categories[] = $item->entity->getName();
    }
    $variables['node_categories'] = implode(', ', $categories);
  }

  elseif ($node->bundle() === 'news' && $variables['view_mode'] === 'full') {
    $facebook_share = 'https://www.facebook.com/sharer/sharer.php?u=' . $node->toUrl()->setAbsolute()->toString();
    $variables['facebook_share_url'] = $facebook_share;
  }
}

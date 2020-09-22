<?php

/**
 * @file
 * Functions to support theming blocks.
 */

use Drupal\node\Entity\Node;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function asebac_theme_suggestions_page_alter(array &$suggestions, array $variables) {
  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node && is_object($node)) {
    $suggestions[] = 'page__' . $node->bundle();
  }
}

/**
 * Implements hook_preprocess_page().
 */
function asebac_preprocess_page(&$variables) {
  // Node pages.
  if (isset($variables['node']) && $variables['node'] instanceof Node) {
    $node = $variables['node'];
    $node_bundles = ['credit', 'landing_page', 'agreement', 'news'];
    if (in_array($node->bundle(), $node_bundles, TRUE)) {
      unset($variables['page']['content']['asebac_page_title']);
    }
  }
}

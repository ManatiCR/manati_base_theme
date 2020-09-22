<?php

/**
 * @file
 * Functions to support theming paragraphs.
 */

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function asebac_theme_suggestions_paragraph_alter(&$suggestions, $variables) {
  $paragraph = $variables['elements']['#paragraph'];
  $suggestions[] = 'paragraph__' . $paragraph->bundle() . '__' . $paragraph->view_mode;
  $parent = $paragraph->getParentEntity();
  if ($parent) {
    $suggestions[] = 'paragraph__' . $parent->bundle() . '__' . $paragraph->bundle();
  }
}

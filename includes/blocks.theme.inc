<?php

/**
 * @file
 * Functions to support theming blocks.
 */

use Drupal\image\Entity\ImageStyle;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function asebac_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // Provide suggestion for block templates by custom block type.
  if (!empty($variables['elements']['content']['#block_content'])) {
    $block = $variables['elements']['content']['#block_content'];
    // Add `block--BLOCK-TYPE.html.twig`.
    $suggestions[] = 'block__' . $block->bundle();
    $view_mode = $variables['elements']['#configuration']['view_mode'];
    if (!empty($view_mode)) {
      // Add `block--BLOCK-TYPE--VIEW-MODE.html.twig`.
      $suggestions[] = 'block__' . $block->bundle() . '__' . $view_mode;
    }
  }
}

/**
 * Implements hook_preprocess_block().
 */
function asebac_preprocess_block(&$variables) {
  if ($variables['base_plugin_id'] == 'inline_block') {
    $block = $variables['content']['#block_content'];
    // Basic Card Component.
    if ($block->bundle() == 'basic_card') {
      // Variation field.
      if (!$block->field_basic_card_variation->isEmpty()) {
        switch ($block->field_basic_card_variation->value) {
          case 'bg-withe':
            $variables['heading_modifier'] = 'underline';
            $variables['button_modifier'] = 'alt';
            break;

          case 'bg-withe-border':
            $variables['field_basic_card_variation'] = 'outline';
            $variables['button_modifier'] = 'alt';
            break;

          case 'bg-red':
            $variables['field_basic_card_variation'] = 'alt';
            $variables['button_modifier'] = 'alt-red';
            break;

          case 'text-red':
            $variables['field_basic_card_variation'] = 'border';
            $variables['heading_modifier'] = 'underline';
            $variables['container_modifier'] = 'border';
            $variables['button_modifier'] = '';
            break;

          case 'text-red-no-border':
            $variables['field_basic_card_variation'] = 'red';
            $variables['heading_modifier'] = 'underline';
            $variables['container_modifier'] = 'red';
            $variables['button_modifier'] = '';
            break;

          default:
            $variables['heading_modifier'] = 'underline';
            $variables['button_modifier'] = 'alt';
            break;
        }
      }
      // Paragraph field of File or Link.
      if (!$block->field_link_file_two_items->isEmpty()) {
        foreach ($block->field_link_file_two_items as $item) {
          // Link Paragraph.
          if ($item->entity->getType() == 'link') {
            $variables['field_link_file_two_items'][] = [
              'content' => $item->entity->field_link->title,
              'url' => $item->entity->field_link->first()->getUrl()->toString(),
              'type' => 'link',
              'icon' => 'arrow',
              'modifiers' => $variables['button_modifier'],
            ];
          }
          // File Paragraph.
          if ($item->entity->getType() == 'file') {
            if (!$item->entity->field_file->isEmpty()) {
              $media_entity = $item->entity->field_file->entity;
              $variables['field_link_file_two_items'][] = [
                'content' => $media_entity->field_media_file->description ?: $media_entity->name->value,
                'url' => $media_entity->field_media_file->entity->url(),
                'type' => 'link',
                'icon' => 'arrow',
                'modifiers' => $variables['button_modifier'],
              ];
            }
          }
        }
      }
    }
    // Basic Block Component.
    elseif ($block->bundle() == 'basic_block') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
    }
    // Button List Component.
    elseif ($block->bundle() == 'button_list') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Variation field.
      if (!$block->field_button_list_variation->isEmpty()) {
        switch ($block->field_button_list_variation->value) {
          case 'bg-red':
            $variables['button_modifiers'] = 'alt';
            break;

          case 'bg-gray':
            $variables['field_button_list_variation'] = 'alt';
            $variables['button_modifiers'] = 'border-bottom';
            break;

          default:
            $variables['button_modifiers'] = 'alt';
            break;
        }
      }
      // Paragraph field of File or Link.
      if (!$block->field_link_file_unlimited->isEmpty()) {
        foreach ($block->field_link_file_unlimited as $item) {
          // Link Paragraph.
          if ($item->entity->getType() == 'link') {
            $variables['field_link_file_unlimited'][] = [
              'content' => $item->entity->field_link->title,
              'url' => $item->entity->field_link->first()->getUrl()->toString(),
            ];
          }
          // File Paragraph.
          if ($item->entity->getType() == 'file') {
            if (!$item->entity->field_file->isEmpty()) {
              $media_entity = $item->entity->field_file->entity;
              if ($media_entity) {
                $variables['field_link_file_unlimited'][] = [
                  'content' => $media_entity->field_media_file->description ?: $media_entity->name->value,
                  'url' => $media_entity->field_media_file->entity->url(),
                ];
              }
            }
          }
        }
      }
    }
    // Rounded Card Component.
    elseif ($block->bundle() == 'rounded_card') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Image field.
      if (!$block->field_image->isEmpty()) {
        $uri = $block->field_image->entity->field_media_image->entity->uri->value;
        $style = ImageStyle::load('component_230_230_retinafied');
        $variables['field_image']['src'] = $style->buildUrl($uri);
        $variables['field_image']['alt'] = $block->field_image->entity->field_media_image->alt;
      }
      // Paragraph field of File or Link.
      if (!$block->field_link_file->isEmpty()) {
        // Link Paragraph.
        if ($block->field_link_file->first()->entity->getType() == 'link') {
          $variables['field_link_file'][] = [
            'content' => $block->field_link_file->first()->entity->field_link->title,
            'url' => $block->field_link_file->first()->entity->field_link->first()->getUrl()->toString(),
            'type' => 'link',
            'modifiers' => 'alt-red',
          ];

        }
        // File Paragraph.
        if ($block->field_link_file->first()->entity->getType() == 'file') {
          if (!$block->field_link_file->first()->entity->field_file->isEmpty()) {
            $media_entity = $block->field_link_file->first()->entity->field_file->entity;
            $variables['field_link_file'][] = [
              'content' => $media_entity->field_media_file->description ?: $media_entity->name->value,
              'url' => $media_entity->field_media_file->entity->url(),
              'type' => 'link',
              'modifiers' => 'alt-red',
            ];
          }
        }
      }
    }
    // Basic Card with Image Component.
    elseif ($block->bundle() == 'basic_card_image') {
      // Variation field.
      if (!$block->field_basic_card_image_variation->isEmpty()) {
        switch ($block->field_basic_card_image_variation->value) {
          case 'square-img':
            $variables['button_modifier'] = 'alt';
            $variables['card_modifier'] = 'image';
            break;

          case 'rounded-img':
            $variables['card_modifier'] = 'image-svg';
            $variables['image_svg_icon'] = 'circles-md';
            $variables['button_modifier'] = '';
            break;

          default:
            $variables['button_modifier'] = 'alt';
            $variables['card_modifier'] = 'image';
            break;
        }
      }
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Image field.
      if (!$block->field_image->isEmpty()) {
        $uri = $block->field_image->entity->field_media_image->entity->uri->value;
        $style = ImageStyle::load('component_280_260_retinafied');
        $variables['field_image']['src'] = $style->buildUrl($uri);
        $variables['field_image']['alt'] = $block->field_image->entity->field_media_image->alt;
      }
      // Paragraph field of File or Link.
      if (!$block->field_link_file_two_items->isEmpty()) {
        foreach ($block->field_link_file_two_items as $item) {
          // Link Paragraph.
          if ($item->entity->getType() == 'link') {
            $variables['field_link_file_two_items'][] = [
              'content' => $item->entity->field_link->title,
              'url' => $item->entity->field_link->first()->getUrl()->toString(),
              'type' => 'link',
              'icon' => 'arrow',
              'modifiers' => $variables['button_modifier'],
            ];
          }
          // File Paragraph.
          if ($item->entity->getType() == 'file') {
            if (!$item->entity->field_file->isEmpty()) {
              $media_entity = $item->entity->field_file->entity;
              $variables['field_link_file_two_items'][] = [
                'content' => $media_entity->field_media_file->description ?: $media_entity->name->value,
                'url' => $media_entity->field_media_file->entity->url(),
                'type' => 'link',
                'icon' => 'arrow',
                'modifiers' => $variables['button_modifier'],
              ];
            }
          }
        }
      }
    }
    // Heading Component.
    elseif ($block->bundle() == 'heading') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Image field.
      if (!$block->field_image->isEmpty()) {
        $uri = $block->field_image->entity->field_media_image->entity->uri->value;
        $style = ImageStyle::load('component_618_280_retinafied');
        $variables['field_image']['src'] = $style->buildUrl($uri);
        $variables['field_image']['alt'] = $block->field_image->entity->field_media_image->alt;
      }
      // Link field.
      if (!$block->field_link_two_items->isEmpty()) {
        foreach ($block->field_link_two_items as $item) {
          $variables['field_link_two_items'][] = [
            'content' => $item->title,
            'url' => $item->getUrl()->toString(),
            'type' => 'link',
            'icon' => 'arrow',
            'modifiers' => 'alt-red',
          ];
        }
      }
    }
    // Contact Information Component.
    elseif ($block->bundle() == 'contact_information') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Phone field.
      if (!$block->field_phone->isEmpty()) {
        $variables['field_phone'] = $block->field_phone->value;
      }
      // Link field.
      if (!$block->field_link->isEmpty()) {
        $variables['field_link'] = [
          'content' => $block->field_link->title,
          'url' => $block->field_link->first()->getUrl()->toString(),
          'modifiers' => 'outline',
        ];
      }
      // Schedule field.
      if (!$block->field_plain_text->isEmpty()) {
        $variables['field_plain_text'] = $block->field_plain_text->value;
      }
      // Social Netwoks heading field.
      if (!$block->field_plain_text_social_network->isEmpty()) {
        $variables['field_plain_text_social_network'] = $block->field_plain_text_social_network->value;
      }
      // Paragraph field of Social Network.
      if (!$block->field_social_network_unlimited->isEmpty()) {
        $style = ImageStyle::load('social_network_icon_height_20');
        foreach ($block->field_social_network_unlimited as $item) {
          // Social Network Paragraph.
          if ($item->entity->getType() == 'social_network') {
            if (!$item->entity->field_social_network_icon->isEmpty()) {
              $image_file = $item->entity->field_social_network_icon->entity;
              $mime_type = $image_file->getMimeType();
              $image_url = ($mime_type == 'image/svg+xml') ? file_create_url($image_file->getFileuri()) : $style->buildUrl($image_file->getFileuri());
              $variables['field_social_network_unlimited'][] = [
                'src' => $image_url,
                'url' => $item->entity->field_link->first()->getUrl()->toString(),
                'alt' => $item->entity->field_link->title,
              ];
            }
          }
        }
      }
    }
    // Accordion Component.
    elseif ($block->bundle() == 'accordion') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Paragraph field of Collapsible item.
      if (!$block->field_collapsible_item_unlimited->isEmpty()) {
        foreach ($block->field_collapsible_item_unlimited as $item) {
          // Collapsible item Paragraph.
          if ($item->entity->getType() == 'collapsible_item') {
            $variables['field_collapsible_item_unlimited'][] = [
              'title' => $item->entity->field_title->value,
              'content' => $item->entity->field_description->processed,
            ];
          }
        }
      }
    }
    // Accordion Component.
    elseif ($block->bundle() == 'carousel') {
      if (!$block->field_slide_unlimited->isEmpty()) {
        foreach ($block->field_slide_unlimited as $item) {
          // Build the carousel slide menu.
          $variables['carousel_slides_menu'][] = [
            'menu__content' => $item->entity->field_slide_identifier->value,
          ];
        }
      }
    }
    elseif ($block->bundle() === 'directors_board') {
      // Title and title heading fields.
      if (!$block->field_title->isEmpty()) {
        $variables['field_title'] = $block->field_title->value;
        $variables['field_title_heading_level'] = $block->field_title_heading_level->value;
      }
      // Body field.
      if (!$block->body->isEmpty()) {
        $variables['body'] = $block->body->processed;
      }
      // Description field (footnote).
      if (!$block->field_description->isEmpty()) {
        $variables['field_description'] = $block->field_description->processed;
      }
    }
  }
  elseif ($variables['base_plugin_id'] === 'block_content') {
    $block = $variables['content']['#block_content'];
    // Site footer block.
    if ($block->bundle() === 'footer') {
      // Disable the block cache.
      $variables['#cache']['max-age'] = 0;
      if (!$block->field_plain_text->isEmpty()) {
        $variables['footer_phone'] = $block->field_plain_text->value;
      }
      $variables['footer_ctas'] = [];
      foreach ($block->field_link_two_items as $item) {
        $variables['footer_ctas'][] = [
          'title' => $item->title,
          'url' => $item->getUrl()->toString(),
        ];
      }
      $variables['footer_links'] = [];
      foreach ($block->field_secondary_links as $item) {
        $variables['footer_links'][] = [
          'title' => $item->title,
          'url' => $item->getUrl()->toString(),
        ];
      }
      $variables['footer_social_links'] = [];
      $style = ImageStyle::load('social_network_icon_height_20');
      foreach ($block->field_social_network_unlimited->referencedEntities() as $paragraph) {
        if (!($paragraph->field_social_network_icon->isEmpty() || $paragraph->field_link->isEmpty())) {
          $image_file = $paragraph->field_social_network_icon->entity;
          $mime_type = $image_file->getMimeType();
          $image_url = ($mime_type == 'image/svg+xml') ? file_create_url($image_file->getFileuri()) : $style->buildUrl($image_file->getFileuri());
          $variables['footer_social_links'][] = [
            'src' => $image_url,
            'url' => $paragraph->field_link->first()->getUrl()->toString(),
            'alt' => $paragraph->field_link->title,
          ];
        }
      }
    }
  }
}

import React from 'react';
import { useEffect } from '@storybook/client-api';
import carousel from './carousel.twig';
import carouselData from './carousel.yml';
import './carousel';

/**
 * Storybook Definition.
 */
export default {
  title: 'Molecules/Carousel',
};

export const carouselExample = () => {
  useEffect(() => Drupal.attachBehaviors(), []);
  return (
    <div
      dangerouslySetInnerHTML={{
        __html: carousel(carouselData),
      }}
    />
  );
};

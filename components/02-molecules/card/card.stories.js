import React from 'react';

import card from './card.twig';

import cardData from './card.yml';
import cardImgData from './card-img.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Molecules/Cards' };

export const cardExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardData) }} />
);

export const cardWithImageExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardImgData) }} />
);

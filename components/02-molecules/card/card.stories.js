import React from 'react';

import card from './card.twig';
import cardBasic from './card-basic.twig';

import cardData from './card.yml';
import cardAltData from './card-alt.yml';
import cardOutlineData from './card-outline.yml';
import cardRoundedData from './card-rounded.yml';
import cardImgData from './card-img.yml';
import cardImgSvgData from './card-img-svg.yml';
import cardBorderData from './card-border.yml';
import cardRedData from './card-red.yml';
import cardBasicData from './card-basic.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Molecules/Cards' };

export const cardExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardData) }} />
);

export const cardAltExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardAltData) }} />
);

export const cardOutlineExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardOutlineData) }} />
);

export const cardRoundedExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardRoundedData) }} />
);

export const cardWithImageExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardImgData) }} />
);

export const cardWithImageAndSVGExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardImgSvgData) }} />
);

export const cardBorderExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardBorderData) }} />
);

export const cardRedExample = () => (
  <div dangerouslySetInnerHTML={{ __html: card(cardRedData) }} />
);

export const cardBasicExample = () => (
  <div dangerouslySetInnerHTML={{ __html: cardBasic(cardBasicData) }} />
);

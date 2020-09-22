import React from 'react';
import { useEffect } from '@storybook/client-api';
import { withKnobs, select } from '@storybook/addon-knobs';
import steps from './steps.twig';
import stepsData from './steps.yml';
import './steps';

/**
 * Storybook Definition.
 */
export default {
  title: 'Molecules/Steps',
  decorators: [withKnobs],
};

export const stepsExample = () => {
  useEffect(() => Drupal.attachBehaviors(), []);

  const headingPosition = select(
    'Heading Position',
    ['center', 'left'],
    ['center'],
  );

  stepsData.steps__heading__modifiers = [headingPosition];

  return (
    <div
      dangerouslySetInnerHTML={{
        __html: steps(stepsData),
      }}
    />
  );
};

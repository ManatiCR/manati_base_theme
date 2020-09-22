import React from 'react';
import { useEffect } from '@storybook/client-api';

import './accordion';

import accordion from './accordion.twig';
import accordionOneColData from './accordion-one-col.yml';
import accordionTwoColData from './accordion-two-col.yml';
/**
 * Storybook Definition.
 */
export default {
  title: 'Molecules/Accordion',
};

export const AccordionOneColExample = () => {
  useEffect(() => Drupal.attachBehaviors(), []);
  return (
    <div dangerouslySetInnerHTML={{ __html: accordion(accordionOneColData) }} />
  );
};

export const AccordionTwoColExample = () => {
  useEffect(() => Drupal.attachBehaviors(), []);
  return (
    <div dangerouslySetInnerHTML={{ __html: accordion(accordionTwoColData) }} />
  );
};

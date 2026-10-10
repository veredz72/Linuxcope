import { TestBed } from '@angular/core/testing';
import { Sharedobject } from './sharedobject';

describe('Sharedobject', () => {
  let service: Sharedobject;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(Sharedobject);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});

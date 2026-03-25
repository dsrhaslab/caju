/**
 * @file caju.h
 * @author Andre Lucena | Fabio Souza | Goncalo Sousa
 * @brief Declaration of the Caju class
 * @version 0.1
 * @date 2026-03-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

/**
 * @brief Caju class represents a simple example class.
 * 
 */
class Caju {
  public:
    Caju();
    Caju(Caju&&)                 = default;
    Caju(const Caju&)            = default;
    Caju& operator=(Caju&&)      = default;
    Caju& operator=(const Caju&) = default;
    ~Caju();

  private:
};


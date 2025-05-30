package org.url.urlshortenerbe.dtos.requests;

import jakarta.validation.constraints.NotBlank;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class IntrospectTokenRequest {
    @NotBlank(message = "Token is required")
    private String token;
}
